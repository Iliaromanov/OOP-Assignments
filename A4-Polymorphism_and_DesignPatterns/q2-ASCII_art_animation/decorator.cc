#include "decorator.h"

Decorator::Decorator(AsciiArt *component) : component{component} {}
Decorator::~Decorator() { delete component; }
