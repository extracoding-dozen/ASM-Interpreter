#ifndef PRINTER_H
#define PRINTER_H

template <typename... Args>

class Printer {
public:
    virtual void Print(Args... args) = 0;
    virtual ~Printer = default;
};


#endif