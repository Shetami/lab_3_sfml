#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>

using namespace std;
using namespace sf;

sf::Mutex mutex;

sf::CircleShape circle;
sf::CircleShape triangle;

int winXsize = 900;
int winYsize = 900;

int inputInt(string message, int min, int max)
{
    int value = 0;
    cout << message;
    if ((!(cin >> value)) || value < min || value > max)
    {
        cout << "Переменная введена некорректно!\n";
        cin.clear();
    }
    else return value;
}



void DrawCircle(int R)
{
    int X = winXsize - 2*R - 50;
    int Y = 50;
    float dx = -5.0f;
    float dy = 0.0f;
    circle.setRadius(R);
    circle.setFillColor(Color::Red);
    circle.setPosition(X, Y);
    for (int i = 0; i < 100; i++)
    {
        circle.move(dx, dy);
        sleep(milliseconds(50));
    }
    return;
}

void DrawTriangle(int R)
{
    int X = winXsize / 2;
    int Y = winYsize - 2*R; 
    float dx = 0.0f;
    float dy = -1.5f;
    triangle.setRadius(R);
    triangle.setPointCount(3);
    triangle.setFillColor(Color::Blue);
    triangle.setPosition(X, Y);
    for (int i = 0; i < 100; i++)
    {
        triangle.move(dx, dy);
        sleep(milliseconds(50));
    }
    return;
}

int main()
{
    setlocale(LC_CTYPE, "Russian");
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);


    int R1 = inputInt("Введите радиус круга (1-100): ", 1, 100);
    int R2 = inputInt("Введите радиус окружности, описыыающей треугольник (1-200): ", 1, 200);

    sf::RenderWindow window(VideoMode(winXsize, winYsize), L"Составные фигуры");

    sf::Thread thread1(&DrawCircle, R1);
    thread1.launch();

    sf::Thread thread2(&DrawTriangle, R2);
    thread2.launch();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        mutex.lock();
        window.clear();
        window.draw(circle);
        window.draw(triangle);
        window.display();
        mutex.unlock();
    }

    cout << endl;
    cout << "Введите любую клавишу для завершения программы  ... ";
    _getch();
    return 0;
}
