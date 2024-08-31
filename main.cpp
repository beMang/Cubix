#include "app/instance.hpp"
#include <string>

int main()
{
    app::Instance instance = app::Instance();
    instance.init();
    instance.loop();
    return 0;
}
