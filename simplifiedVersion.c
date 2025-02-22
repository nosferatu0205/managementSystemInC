#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Student
{
    char id[10];
    char name[20];
    char email[30];
    int num_courses;
};

struct Course
{
    char student_id[10];
    char name[20];
};

struct Student students[50];
struct Course courses[100];
int total_students = 0;
int total_courses = 0;

// File operation functions
void save_to_file();
void load_from_file();

void display_menu();
void add_student();
void list_students();
void search_student();
void delete_student();
void clear_screen();

int main()
{
    load_from_file(); // Load existing data when program starts

    int choice;
    while (1)
    {
        display_menu();
        scanf("%d", &choice);
        clear_screen();

        switch (choice)
        {
        case 1:
            add_student();
            save_to_file(); // Save after adding
            break;
        case 2:
            list_students();
            break;
        case 3:
            search_student();
            break;
        case 4:
            delete_student();
            save_to_file(); // Save after deleting
            break;
        case 5:
            save_to_file(); // Save before exiting
            printf("Goodbye!\n");
            return 0;
        default:
            printf("Invalid choice. Try again.\n");
        }
    }
}

void save_to_file()
{
    // Save students
    FILE *student_file = fopen("students.dat", "wb");
    if (student_file != NULL)
    {
        fwrite(&total_students, sizeof(int), 1, student_file);
        fwrite(students, sizeof(struct Student), total_students, student_file);
        fclose(student_file);
    }

    // Save courses
    FILE *course_file = fopen("courses.dat", "wb");
    if (course_file != NULL)
    {
        fwrite(&total_courses, sizeof(int), 1, course_file);
        fwrite(courses, sizeof(struct Course), total_courses, course_file);
        fclose(course_file);
    }
}

void load_from_file()
{
    // Load students
    FILE *student_file = fopen("students.dat", "rb");
    if (student_file != NULL)
    {
        fread(&total_students, sizeof(int), 1, student_file);
        fread(students, sizeof(struct Student), total_students, student_file);
        fclose(student_file);
    }

    // Load courses
    FILE *course_file = fopen("courses.dat", "rb");
    if (course_file != NULL)
    {
        fread(&total_courses, sizeof(int), 1, course_file);
        fread(courses, sizeof(struct Course), total_courses, course_file);
        fclose(course_file);
    }
}

void display_menu()
{
    printf("\n=== Student Management System ===\n");
    printf("1. Add Student\n");
    printf("2. List All Students\n");
    printf("3. Search Student\n");
    printf("4. Delete Student\n");
    printf("5. Exit\n");
    printf("Choose an option: ");
}

void add_student()
{
    printf("=== Add New Student ===\n");

    struct Student s;
    printf("Enter ID: ");
    scanf("%s", s.id);
    printf("Enter Name: ");
    scanf(" %[^\n]s", s.name);
    printf("Enter Email: ");
    scanf("%s", s.email);
    printf("Enter number of courses (max 4): ");
    scanf("%d", &s.num_courses);

    students[total_students] = s;

    // Add courses
    for (int i = 0; i < s.num_courses; i++)
    {
        struct Course c;
        strcpy(c.student_id, s.id);
        printf("Enter Course %d name: ", i + 1);
        scanf(" %[^\n]s", c.name);
        courses[total_courses++] = c;
    }

    total_students++;
    printf("\nStudent added successfully!\n");
}

void list_students()
{
    printf("=== All Students ===\n");
    printf("ID\tName\tEmail\tCourses\n");
    printf("--------------------------------\n");

    for (int i = 0; i < total_students; i++)
    {
        printf("%s\t%s\t%s\t%d\n",
               students[i].id,
               students[i].name,
               students[i].email,
               students[i].num_courses);

        // List courses for this student
        for (int j = 0; j < total_courses; j++)
        {
            if (strcmp(courses[j].student_id, students[i].id) == 0)
            {
                printf("\t- %s\n", courses[j].name);
            }
        }
        printf("\n");
    }
}

void search_student()
{
    char search_id[10];
    printf("Enter student ID to search: ");
    scanf("%s", search_id);

    for (int i = 0; i < total_students; i++)
    {
        if (strcmp(students[i].id, search_id) == 0)
        {
            printf("\nStudent found:\n");
            printf("ID: %s\n", students[i].id);
            printf("Name: %s\n", students[i].name);
            printf("Email: %s\n", students[i].email);
            printf("Courses:\n");

            for (int j = 0; j < total_courses; j++)
            {
                if (strcmp(courses[j].student_id, search_id) == 0)
                {
                    printf("- %s\n", courses[j].name);
                }
            }
            return;
        }
    }
    printf("Student not found.\n");
}

void delete_student()
{
    char delete_id[10];
    printf("Enter student ID to delete: ");
    scanf("%s", delete_id);

    for (int i = 0; i < total_students; i++)
    {
        if (strcmp(students[i].id, delete_id) == 0)
        {
            // Remove student by shifting array
            for (int j = i; j < total_students - 1; j++)
            {
                students[j] = students[j + 1];
            }
            total_students--;

            // Remove associated courses
            for (int j = 0; j < total_courses; j++)
            {
                if (strcmp(courses[j].student_id, delete_id) == 0)
                {
                    for (int k = j; k < total_courses - 1; k++)
                    {
                        courses[k] = courses[k + 1];
                    }
                    total_courses--;
                    j--; // Recheck current index after shift
                }
            }

            printf("Student deleted successfully!\n");
            return;
        }
    }
    printf("Student not found.\n");
}

void clear_screen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
