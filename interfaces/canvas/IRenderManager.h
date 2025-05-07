#ifndef I_RENDER_MANAGER_H
#define I_RENDER_MANAGER_H

#include <vector>

template <class T>
class IRenderManager {
    protected:
        int width;
        int height;

    public:
        IRenderManager(int, int) = default;
        virtual ~IRenderManager() = default;

        virtual void render(vector<T>) = 0;
};

#endif //I_RENDER_MANAGER_H