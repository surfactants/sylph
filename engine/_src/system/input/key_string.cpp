#include <system/input/key_string.hpp>

std::map<sf::Keyboard::Key, std::string> Key_String::key_to_string;
std::map<std::string, sf::Keyboard::Key> Key_String::string_to_key;

Key_String::Key_String()
{
    if (key_to_string.empty()) {
        init();
    }
}

std::string Key_String::toString(const sf::Keyboard::Key& key)
{
    std::string str;
    if (key_to_string.contains(key)) {
        str = key_to_string[key];
    }
    return str;
}

sf::Keyboard::Key Key_String::toKey(const std::string& str)
{
    sf::Keyboard::Key key { sf::Keyboard::Unknown };
    if (string_to_key.contains(str)) {
        key = string_to_key[str];
    }
    return key;
}

void Key_String::init()
{
#define KEY_INSERT(x)                                           \
    key_to_string.insert({ sf::Keyboard::x, std::string(#x) }); \
    string_to_key.insert({ std::string(#x), sf::Keyboard::x });

    KEY_INSERT(Unknown);
    KEY_INSERT(A);
    KEY_INSERT(B);
    KEY_INSERT(C);
    KEY_INSERT(D);
    KEY_INSERT(E);
    KEY_INSERT(F);
    KEY_INSERT(G);
    KEY_INSERT(H);
    KEY_INSERT(I);
    KEY_INSERT(J);
    KEY_INSERT(K);
    KEY_INSERT(L);
    KEY_INSERT(M);
    KEY_INSERT(N);
    KEY_INSERT(O);
    KEY_INSERT(P);
    KEY_INSERT(Q);
    KEY_INSERT(R);
    KEY_INSERT(S);
    KEY_INSERT(T);
    KEY_INSERT(U);
    KEY_INSERT(V);
    KEY_INSERT(W);
    KEY_INSERT(X);
    KEY_INSERT(Y);
    KEY_INSERT(Z);
    KEY_INSERT(Num0);
    KEY_INSERT(Num1);
    KEY_INSERT(Num2);
    KEY_INSERT(Num3);
    KEY_INSERT(Num4);
    KEY_INSERT(Num5);
    KEY_INSERT(Num6);
    KEY_INSERT(Num7);
    KEY_INSERT(Num8);
    KEY_INSERT(Num9);
    KEY_INSERT(LControl);
    KEY_INSERT(LShift);
    KEY_INSERT(LAlt);
    KEY_INSERT(LSystem);
    KEY_INSERT(RControl);
    KEY_INSERT(RShift);
    KEY_INSERT(RAlt);
    KEY_INSERT(RSystem);
    KEY_INSERT(Menu);
    KEY_INSERT(LBracket);
    KEY_INSERT(RBracket);
    KEY_INSERT(SemiColon);
    KEY_INSERT(Comma);
    KEY_INSERT(Period);
    KEY_INSERT(Quote);
    KEY_INSERT(Slash);
    KEY_INSERT(BackSlash);
    KEY_INSERT(Tilde);
    KEY_INSERT(Equal);
    KEY_INSERT(Dash);
    KEY_INSERT(Space);
    KEY_INSERT(Return);
    KEY_INSERT(BackSpace);
    KEY_INSERT(Tab);
    KEY_INSERT(PageUp);
    KEY_INSERT(PageDown);
    KEY_INSERT(End);
    KEY_INSERT(Home);
    KEY_INSERT(Insert);
    KEY_INSERT(Delete);
    KEY_INSERT(Add);
    KEY_INSERT(Subtract);
    KEY_INSERT(Multiply);
    KEY_INSERT(Divide);
    KEY_INSERT(Left);
    KEY_INSERT(Right);
    KEY_INSERT(Up);
    KEY_INSERT(Down);
    KEY_INSERT(Numpad0);
    KEY_INSERT(Numpad1);
    KEY_INSERT(Numpad2);
    KEY_INSERT(Numpad3);
    KEY_INSERT(Numpad4);
    KEY_INSERT(Numpad5);
    KEY_INSERT(Numpad6);
    KEY_INSERT(Numpad7);
    KEY_INSERT(Numpad8);
    KEY_INSERT(Numpad9);
    KEY_INSERT(F1);
    KEY_INSERT(F2);
    KEY_INSERT(F3);
    KEY_INSERT(F4);
    KEY_INSERT(F5);
    KEY_INSERT(F6);
    KEY_INSERT(F7);
    KEY_INSERT(F8);
    KEY_INSERT(F9);
    KEY_INSERT(F10);
    KEY_INSERT(F11);
    KEY_INSERT(F12);
    KEY_INSERT(F13);
    KEY_INSERT(F14);
    KEY_INSERT(F15);
    KEY_INSERT(Pause);

    static_assert(sf::Keyboard::KeyCount == 101, "Number of SFML keys has changed");
#undef KEY_INSERT
}
