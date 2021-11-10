#ifndef TEXTOBS_H
#define TEXTOBS_H
#include "observer.h"
#include "studio.h"

class TextObserver : public Observer {
    Studio *subject;
    int top, bottom, left, right;

    public:
        TextObserver(Studio *cavas, int top, int bottom, int left, int right);
        void notify() override;
        ~TextObserver();
};
#endif