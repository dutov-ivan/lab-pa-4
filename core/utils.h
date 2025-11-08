//
// Created by ivan on 11/8/25.
//

#ifndef LAB4_PA_QT_UTILS_H
#define LAB4_PA_QT_UTILS_H
#include <stdexcept>

// Source - https://stackoverflow.com/a
// Posted by MatrixManAtYrService
// Retrieved 2025-11-08, License - CC BY-SA 3.0

class NotImplemented : public std::logic_error {
public:
    NotImplemented() : std::logic_error("Function not yet implemented") {
    };
};


#endif //LAB4_PA_QT_UTILS_H
