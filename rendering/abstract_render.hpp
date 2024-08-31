#ifndef ABSTRACT_RENDER_HPP
#define ABSTRACT_RENDER_HPP

namespace rendering
{
    class AbstractRender
    {
    public:
        virtual void init() = 0;
        virtual void render() = 0;
        virtual void clean() = 0;

        virtual ~AbstractRender() = default;
    };
} // namespace rendering

#endif // ABSTRACT_RENDER_HPP