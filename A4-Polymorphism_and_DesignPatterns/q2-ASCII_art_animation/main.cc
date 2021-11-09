#include <iostream>
#include "asciiart.h"
#include "blank.h"
#include "studio.h"
#include "filledbox.h"
#include "blinkingbox.h"
#include "movingbox.h"
#include "maskbox.h"

int main () {
  AsciiArt *canvas = new Blank;

  Studio s{canvas};

  std::string command;

  while (std::cin >> command) {
    if (command == "render" ) {
      s.render();
    }
    else if (command == "animate") {
      int n;
      std::cin >> n;
      s.animate(n);
    }
    else if (command == "reset") {
      s.reset();
    }
    else if (command == "filledbox") {
      int top, bottom, left, right;
      char what;
      std::cin >> top >> bottom >> left >> right >> what;
      s.picture() = new Filledbox{top, bottom, left, right, what, s.picture()};
    }
    else if (command == "blinkingbox") {
      int top, bottom, left, right;
      char what;
      std::cin >> top >> bottom >> left >> right >> what;
      s.picture() = new Blinkingbox{top, bottom, left, right, what, s.picture()};
    }
    else if (command == "movingbox") {
      int top, bottom, left, right;
      char what, dir;
      std::cin >> top >> bottom >> left >> right >> what >> dir;
      s.picture() = new Movingbox{top, bottom, left, right, what, dir, s.picture()};
    }
    else if (command == "maskbox") {
      int top, bottom, left, right;
      char what;
      std::cin >> top >> bottom >> left >> right >> what;
      s.picture() = new Maskbox{top, bottom, left, right, what, s.picture()};
    }
  }
}
