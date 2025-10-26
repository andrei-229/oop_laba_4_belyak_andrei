#include "../include/Point.h"
#include "../include/Figure.h"
#include "../include/Hexagon.h"
#include "../include/Octagon.h"
#include "../include/Triangle.h"
#include "../include/Array.h"
#include <memory>
#include <iostream>

template <typename T>
double calculate_total_area(const Array<std::shared_ptr<Figure<T>>> &figures);

template <typename T>
void print_all_figures(const Array<std::shared_ptr<Figure<T>>> &figures);

void demonstrate_figures()
{
    std::cout << "=== Geometric Figures Demo ===" << std::endl;

    Array<std::shared_ptr<Figure<double>>> figures;
    std::cout << "Enter figures:\n";
    std::cout << "h - hexagon\n";
    std::cout << "o - octagon\n";
    std::cout << "t - triangle\n";
    std::cout << "q - quit input\n\n";

    char choice;
    while (std::cin >> choice)
    {
        if (choice == 'q')
            break;

        auto hexagon = std::make_shared<Hexagon<double>>();
        auto octagon = std::make_shared<Octagon<double>>();
        auto triangle = std::make_shared<Triangle<double>>();
        
            switch (choice)
            {
            case 'h':
                std::cout << "\n=== Creating Hexagon ===" << std::endl;
                
                std::cin >> *hexagon;
                figures.push_back(hexagon);
                break;
            case 'o':
                std::cout << "\n=== Creating Octagon ===" << std::endl;
                
                std::cin >> *octagon;
                figures.push_back(octagon);
                break;
            case 't':
                std::cout << "\n=== Creating Triangle ===" << std::endl;
                
                std::cin >> *triangle;
                figures.push_back(triangle);
                break;
            default:
                std::cout << "Unknown figure type. Try again.\n";
                continue;
            }
        
    }
    print_all_figures(figures);

    std::cout << "Total area: " << calculate_total_area(figures) << std::endl;

    if (figures.length() > 0){
        std::cout << "\n=== After removing first figure ===" << std::endl;
    figures.erase(0);
    print_all_figures(figures);
    std::cout << "Total area after removal: " << calculate_total_area(figures) << std::endl;
    }
}

void demonstrate_array_with_base_type()
{
    std::cout << "\n=== Array<Figure<int>*> Demo ===" << std::endl;
    Array<Figure<int> *> base_figures;

    auto *hex = new Hexagon<int>();
    std::cout << "Enter Hexagon points:" << std::endl;
    std::cin >> *hex;
    base_figures.push_back(hex);

    auto *tri = new Triangle<int>();
    std::cout << "Enter Triangle points:" << std::endl;
    std::cin >> *tri;
    base_figures.push_back(tri);

    for (size_t i = 0; i < base_figures.size(); ++i)
    {
        base_figures[i]->print(std::cout);
        std::cout << std::endl;
    }

    for (size_t i = 0; i < base_figures.size(); ++i)
    {
        delete base_figures[i];
    }
}

void demonstrate_array_with_derived_type()
{
    std::cout << "\n=== Array<Hexagon<double>> Demo ===" << std::endl;
    Array<Hexagon<double>> hex_array;

    Hexagon<double> hex;
    std::cout << "Enter Hexagon points:" << std::endl;
    std::cin >> hex;

    hex_array.push_back(std::move(hex));

    std::cout << hex_array;
}

int main()
{
    try
    {
        demonstrate_figures();
        demonstrate_array_with_base_type();
        demonstrate_array_with_derived_type();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}