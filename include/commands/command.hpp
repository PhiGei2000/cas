#pragma once
#include <functional>
#include <string>

namespace cas {
    class Engine;
}

namespace cas::commands {
    template<typename T>
    T parseArg(const std::string& arg);

    template<typename TRes, typename... TArgs>
    using CommandFunctor = std::function<TRes(Engine*, TArgs...)>;

    template<typename TRes, typename... TArgs>
    struct Command {
      protected:
        CommandFunctor<TRes, TArgs...> callback;

        template<std::size_t... I>
        inline TRes executeWithArgs(Engine* engine, const std::vector<std::string>& argV, std::index_sequence<I...>) const {
            std::tuple<TArgs...> args = std::make_tuple(std::move(parseArg<TArgs>(argV[I]))...);

            TRes result = callback(engine, std::get<I>(args)...);
            deleteArgs(std::get<I>(args)...);
            return result;
        }

        template<typename T1, typename... T>
        inline static void deleteArgs(T1 arg, T... args) {
            if constexpr (std::is_pointer<T1>::value) {
                delete arg;
            }
            deleteArgs(args...);
        }

        template<typename T1>
        inline static void deleteArgs(T1 arg) {
            if constexpr(std::is_pointer<T1>::value) {
                delete arg;
            }
        }

      public:
        inline Command(const CommandFunctor<TRes, TArgs...>& callback)
            : callback(callback) {
        }

        template<typename Indices = std::make_index_sequence<sizeof...(TArgs)>>
        inline TRes execute(Engine* engine, const std::vector<std::string>& argV) const {
            if constexpr (sizeof...(TArgs) == 0) {
                return callback(engine);
            }
            else {
                return executeWithArgs(engine, argV, Indices{});
            }
        }
    };

} // namespace cas::commands
