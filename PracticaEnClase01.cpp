#include <iostream>
#include <sstream>
#include <windows.h> // Needed for: SetConsoleOutputCP
#include <cstdlib> // Needed for: rand() and srand()
#include <ctime>   // Needed for: time()
#include <conio.h>
#include <iomanip> //Needed for: setprecision
using namespace std;

int** createMatrix(int* pStudents, int* pGrades);
float calculateStudentAverage(int** pMatrix, int aStudent, int aGrades);
void printMatrix(int** pMatrix, int aRows, int aCols);
void calculateAllStudentsAverage(float* aStudentsAverage, int** pMatrix, int aStudents, int aGrades);
void showAllStudentsAverage(float* sStudentsAverage, int** pMatrix, int aStudents);
void calculateBestStudentsAverage(float* aBestStudentsAverage, float* aStudentsAverage);
void showBestStudentsAverage(float* sBestStudentsAverage);
void deleteMatrix(int** aGradesMatrix, int aStudent);

int main()
{
  SetConsoleOutputCP(CP_UTF8); //Permite imprimir caracteres especiales, ej.: á é ñ
  srand(time(0)); // Seed the random number generator using the current time
  
  int students = 0, grades = 0;
  int** gradesMatrix = createMatrix(&students, &grades);

  float* studentAverages = new float[students];
  bool isAveragesSet = false;

  float bestStudentAverages[5];
  bool isBestAveragesSet = false;

  int menuOption = -1;
  while (menuOption != 0)
  {
    system("cls");
    cout << "Seleccione una opción escribiendo el número correspondiente:" << endl;
    cout << "0 -> Salir del programa." << endl;
    cout << "1 -> Mostrar Matriz de Evaluaciones." << endl;
    cout << "2 -> Generar Promedios de Notas de Estudiantes." << endl;
    cout << "3 -> Mostrar Promedios de Notas de Estudiantes." << endl;
    cout << "4 -> Calcular 5 Promedios más altos." << endl;
    cout << "5 -> Mostrar 5 Promedios más altos." << endl;
    cout << "6 -> Recrear Matriz de Evaluaciones." << endl;
    cin >> menuOption;
    if (menuOption == 1)
    {
      printMatrix(gradesMatrix, students, grades);
    }
    else if (menuOption == 2)
    {
      calculateAllStudentsAverage(studentAverages, gradesMatrix, students, grades);
      isAveragesSet = true;
    }
    else if (menuOption == 3)
    {
      if (isAveragesSet) {
        showAllStudentsAverage(studentAverages, gradesMatrix, students);
      }
      else
      {
        cout << "Los promedios aún no han sido calculados." << endl;
        cout << "Presione una tecla para regresar al menú" << endl;
        _getch();
      }
    }
    else if (menuOption == 4)
    {
      if (isAveragesSet)
      {
        calculateBestStudentsAverage(bestStudentAverages, studentAverages);
        isBestAveragesSet = true;
      }
      else
      {
        cout << "Los promedios aún no han sido calculados." << endl;
        cout << "Presione una tecla para regresar al menú" << endl;
        _getch();
      }
    }
    else if (menuOption == 5)
    {
      if (isBestAveragesSet) {
        showBestStudentsAverage(bestStudentAverages);
      }
      else
      {
        cout << "Los cinco mejores promedios aún no han sido calculados." << endl;
        cout << "Presione una tecla para regresar al menú" << endl;
        _getch();
      }
    }
    else if (menuOption == 6)
    {
      deleteMatrix(gradesMatrix, students);
      delete[] studentAverages;
      students = grades = 0;
      gradesMatrix = createMatrix(&students, &grades);
      studentAverages = new float[students];
      isAveragesSet = isBestAveragesSet = false;
    }
  }
  return 0;
}

int** createMatrix(int* pStudents, int* pGrades)
{
  while (*pStudents > 30 || *pStudents < 10) {
    cout << "Digite la cantidad de estudiantes (mínimo 10, máximo 30): ";
    cin >> *pStudents;
  }
  while (*pGrades > 10 || *pGrades < 5) {
    cout << "Digite la cantidad de evaluaciones (mínimo 5, máximo 10): ";
    cin >> *pGrades;
  }
  *pGrades+=1; //adds one column for IDs

  int** aGradesMatrix = new int* [*pStudents];
  for (int i = 0; i < *pStudents; i++) {
    aGradesMatrix[i] = new int[*pGrades];
  }

  for (int rows = 0; rows < *pStudents; rows++) {
    aGradesMatrix[rows][0] = 1000 + rand() % 8999;
    for (int cols = 1; cols < *pGrades; cols++) {
      aGradesMatrix[rows][cols] = (rand() % 21) * 5;
    }
  }
  return aGradesMatrix;
}

void printMatrix(int** pMatrix,int aRows,int aCols)
{
  cout << "Carné\t";

  for (int cols = 1; cols < aCols; cols++)
  {
    cout << "Nota" << cols << "\t"; 
  }
  cout << endl;
  for (int rows = 0; rows < aRows; rows++)
  {
    for (int cols = 0; cols < aCols; cols++)
    {
      cout << pMatrix[rows][cols] << "\t";
    }
    cout << endl;
  }
  cout << "Presione una tecla para regresar al menú" << endl;
  _getch();
}

float calculateStudentAverage(int** pMatrix, int aStudent, int aGrades)
{
  float studentAverage = 0.0f;
  for (int grades = 1; grades < aGrades; grades++)
  {
    studentAverage += pMatrix[aStudent][grades];
  }
  return studentAverage / (aGrades - 1);
}

void calculateAllStudentsAverage(float* aStudentsAverage, int** pMatrix, int aStudents, int aGrades)
{
  for (int students = 0; students < aStudents; students++)
  {
    aStudentsAverage[students] = calculateStudentAverage(pMatrix, students, aGrades);
  }

  int swapTemp;
  for (int i = 0; i < aStudents - 1; ++i) {
    for (int j = 0; j < aStudents - 1 - i; ++j) {
      if (aStudentsAverage[j] < aStudentsAverage[j + 1]) {
        swapTemp = aStudentsAverage[j];
        aStudentsAverage[j] = aStudentsAverage[j + 1];
        aStudentsAverage[j + 1] = swapTemp;
      }
    }
  }

  cout << "Promedios generados.\nPresione una tecla para regresar al menú" << endl;
  _getch();
}

void showAllStudentsAverage(float* aStudentsAverage, int** pMatrix, int aStudents)
{
  for (int students = 0; students < aStudents; students++)
  {
    cout << "ID Estudiante: " << pMatrix[students][0];
    cout << " Promedio: " << fixed << setprecision(2) << aStudentsAverage[students] << endl;
  }
  cout << "Presione una tecla para regresar al menú" << endl;
  _getch();
}
void calculateBestStudentsAverage(float* aBestStudentsAverage, float* aStudentsAverage)
{
  for (int student = 0; student < 5; student++)
  {
    aBestStudentsAverage[student] = aStudentsAverage[student];
  }
  cout << "Cinco mejores promedios generados.\nPresione una tecla para regresar al menú" << endl;
  _getch();
}

void showBestStudentsAverage(float* sBestStudentsAverage)
{
  cout << "Cinco mejores promedios" << endl;
  for (int student = 0; student < 5; student++)
  {
    cout << fixed << setprecision(2) << sBestStudentsAverage[student] << endl;
  }
  cout << "Presione una tecla para regresar al menú" << endl;
  _getch();
}
void deleteMatrix(int** aGradesMatrix, int aStudent)
{
  for (int rows = 0; rows < aStudent; rows++) {
    delete[] aGradesMatrix[rows];
  }
  delete[] aGradesMatrix;
  aGradesMatrix = NULL;
}