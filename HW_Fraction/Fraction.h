#pragma once

#include <iostream>
#include <fstream>

int gcd(int a, int b)
{
    while (b > 0)
    {
        int c = a % b;
        a = b;
        b = c;
    }
    return a;
}
int lcm(int a, int b)
{
    return (a * b) / gcd(a, b);
}

class Fraction
{
private:
    int numerator;
    int denominator;

    void skorot()
    {
        int a = gcd(abs(numerator), denominator);
        if (a != 1)
        {
            numerator /= a;
            denominator /= a;
        }
    }

public:
    Fraction(int _numerator, int _denominator)
    {
        try
        {
            if (_denominator != 0 && _numerator != 0)
            {
                numerator = _numerator;
                denominator = _denominator;
            }
            else if (_numerator != 0)
            {
                numerator = _numerator;
                denominator = 1;
                throw std::invalid_argument(0);
            }
            else
            {
                numerator = 1;
                denominator = _denominator;
                throw std::invalid_argument(0);
            }
        }
        catch (std::invalid_argument)
        {
            std::cerr << "Invalid Argumet: " << 0 << '\n';
        }
    }

    void show() const
    {
        std::cout << "Numerator: " << this->numerator << " Denimonator: " << this->denominator << '\n';
    }

    Fraction operator * (Fraction& b)
    {
        this->numerator *= b.numerator;
        this->denominator *= b.denominator;
        skorot();
        return *this;
    }
    Fraction operator / (Fraction& b)
    {
        try
        {
            if (b.numerator != 0)
            {
                this->numerator *= b.denominator;
                this->denominator *= b.numerator;
                skorot();
                return *this;
            }
            else
            {
                throw std::logic_error(0);
            }
        }
        catch (std::logic_error)
        {
            std::cerr << "Logic Error: " << 0 << '\n';
        }
    }
    Fraction operator - (Fraction& b)
    {
        int unionDenom = lcm(this->denominator, b.denominator);
        if (this->denominator != b.denominator)
        {
            int relNumer = this->numerator * (unionDenom / this->denominator);
            int mulNumer = b.numerator * (unionDenom / b.denominator);
            this->numerator = relNumer - mulNumer;
        }
        else
        {
            this->numerator -= b.numerator;
        }
        this->denominator = unionDenom;
        skorot();
        return *this;
    }
    Fraction operator + (Fraction& b)
    {
        int unionDenom = lcm(this->denominator, b.denominator);
        if (this->denominator != b.denominator)
        {
            int relNumer = this->numerator * (unionDenom / this->denominator);
            int mulNumer = b.numerator * (unionDenom / b.denominator);
            this->numerator = relNumer + mulNumer;
        }
        else
        {
            this->numerator += b.numerator;
        }
        this->denominator = unionDenom;
        skorot();
        return *this;
    }

    void save(const char* path)
    {
        std::ofstream Save(path);
        if (Save.is_open())
        {
            Save << this->numerator << ' ' << this->denominator;
            Save.close();
        }
        else
        {
            std::cout << "File wan not openned\n";
        }
    }
    void load(const char* path)
    {
        std::ifstream Load(path);
        if (Load.is_open())
        {
            Load >> this->numerator >> this->denominator;
            Load.close();
        }
        else
        {
            std::cout << "File was not openned\n";
        }
    }
};