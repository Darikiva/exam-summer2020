#pragma once

namespace exam::ui::meta {

template<typename... Fs>
struct Overload : Fs...
{
    using Fs::operator()...;
};

template<typename... Fs>
Overload(Fs...) -> Overload<Fs...>;
    
} // namespace exam::ui::meta
