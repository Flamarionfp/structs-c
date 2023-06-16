#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "alunos.dat"

void clearScreen() {
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
}

void showMenu() {
  printf("Digite a opcao desejada:\n");
  printf("1 - Apresentar todo conteudo do arquivo\n");
  printf("2 - Apresentar conteudo de um registro\n");
  printf("3 - Cadastrar um registro\n");
  printf("4 - Estatisticas\n");
  printf("5 - Fechar o programa\n");
}

typedef struct {
    int enrollment;
    char name[50];
    float finalGrade;
} Student;

void showFileContents() {
  Student student;
  FILE* file = fopen(FILE_NAME, "rb");

  if (file == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    return;
  }

  clearScreen();

  while (fread(&student, sizeof(Student), 1, file) == 1) {
    printf("Matricula: %d\n", student.enrollment);
    printf("Nome: %s", student.name);
    printf("Nota final: %.2f\n", student.finalGrade);
    printf("\n");
  }

  fclose(file);
}

void showStudentRegister() {
  int enrollment;
  printf("Digite a matricula do aluno: ");
  scanf("%d", &enrollment);
  
  clearScreen();

  Student student;
  FILE* file = fopen(FILE_NAME, "rb");

  if (file == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    return;
  }

  while (fread(&student, sizeof(Student), 1, file) == 1) {
    if (student.enrollment == enrollment) {
      printf("Matricula: %d\n", student.enrollment);
      printf("Nome: %s", student.name);
      printf("Nota final: %.2f\n", student.finalGrade);
      printf("\n");
      return;
    }
  }

  printf("Nao foi encontrado nenhum aluno com a matricula %d.\n", enrollment);
  fclose(file);
}

void registerStudent() {
  Student student;
  printf("Digite o codigo de matricula: ");
  scanf("%d", &student.enrollment);

  printf("Digite o nome do aluno: ");
  getchar();
  fgets(student.name, sizeof(student.name), stdin);

  printf("Digite a nota final: \n");
  scanf("%f", &student.finalGrade);

  clearScreen();

  FILE* file = fopen(FILE_NAME, "ab");

  if (file == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    return;
  }

  fwrite(&student, sizeof(Student), 1, file);
  fclose(file);
}

void calculateStatistics() {
  Student student;
  int quantityOfStudents = 0;
  float totalGrade = 0.0;
  float minGrade = 10.0;
  float maxGrade = 0.0;
  char studentNameMin[50];
  char studentNameMax[50];

  FILE* file = fopen(FILE_NAME, "rb");

  if (file == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    return;
  }

  while (fread(&student, sizeof(Student), 1, file) == 1) {
    quantityOfStudents++;
    totalGrade += student.finalGrade;

    if (student.finalGrade < minGrade) {
      minGrade = student.finalGrade;
      strcpy(studentNameMin, student.name);
    }

    if (student.finalGrade > maxGrade) {
      maxGrade = student.finalGrade;
      strcpy(studentNameMax, student.name);
    }
  }

  fclose(file);

  if (quantityOfStudents == 0) {
    printf("Nenhum aluno cadastrado.\n");
    return;
  }

  float averageGrade = totalGrade / quantityOfStudents;

  printf("Estatisticas da turma:\n");
  printf("Quantidade de alunos: %d\n", quantityOfStudents);
  printf("Media da turma: %.2f\n", averageGrade);
  printf("Aluno com a menor nota: %s", studentNameMin);
  printf("Aluno com a maior nota: %s", studentNameMax);
}

int main() {
  int selectedOption = 0;

  do {
    showMenu();
    scanf("%d", &selectedOption);
    getchar();

    switch (selectedOption) {
      case 1:
        showFileContents();
        break;
      case 2:
        showStudentRegister();
        break;
      case 3:
        registerStudent();
        break;
      case 4:
        calculateStatistics();
        break;
      case 5:
        break;
      default:
        printf("Opcao invalida.\n");
        break;
    }

  } while (selectedOption != 5);

  return 0;
}
