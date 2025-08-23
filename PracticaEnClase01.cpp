#include <iostream>
#include <sstream>
#include <windows.h> // Para SetConsoleOutputCP
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include <conio.h>
using namespace std;

void selectMenuOption(int selection);
void printMatrix(int** pMatrix, int aRows, int aCols);

int main()
{
  SetConsoleOutputCP(CP_UTF8); //Permite imprimir caracteres especiales, ej.: á é ñ
  srand(time(0)); // Seed the random number generator using the current time
  
  int students = 0, grades = 0;
  while (students > 30 || students < 10) {
    cout << "Digite la cantidad de estudiantes (mínimo 10, máximo 30): ";
    cin >> students;
  }
  while (grades > 10 || grades < 5) {
    cout << "Digite la cantidad de evaluaciones (mínimo 5, máximo 10): ";
    cin >> grades;
  }
  grades++; //one for IDs
 
  int** gradesMatrix;
  gradesMatrix = new int* [students];
  for (int i = 0; i < students; i++) {
    gradesMatrix[i] = new int[grades];
  }

  for (int rows = 0; rows < students; rows++) {
    gradesMatrix[rows][0] = 1000 + rand() % 8999;
    for (int cols = 1; cols < grades; cols++) {
      gradesMatrix[rows][cols] = (rand() % 21) * 5;
    }
  }

  int menuOption = -1;
  while (menuOption != 0)
  {
    system("cls");
    cout << "Seleccione una opción escribiendo el número correspondiente:" << endl;
    cout << "0 -> Salir del programa." << endl;
    cout << "1 -> Mostrar Matriz." << endl;
    cout << "2 -> Mostrar Promedios de Notas de Estudiantes." << endl;
    cout << "3 -> Mostrar 5 Promedios más altos." << endl;
    cin >> menuOption;
    if (menuOption == 1)
    {
      printMatrix(gradesMatrix, students, grades);
    }
    else if (menuOption == 2)
    {

    }
    else if (menuOption == 3)
    {

    }
    else if (menuOption == 4)
    {

    }
  }
  return 0;
}

void printMatrix(int** pMatrix,int aRows,int aCols) {
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