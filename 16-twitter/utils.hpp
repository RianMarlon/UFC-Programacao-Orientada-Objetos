#include <iostream>
#include <vector>
#include <sstream>
#include <functional>
#include <map>


#define slambda(x_fn) [](auto& x){ return x_fn; }

namespace utils {

    auto fn_identity = slambda(x);
    //dereferencing
    auto fn_deref = slambda(*x);
    auto fn_pair_key = slambda(x.first);
    auto fn_pair_value = slambda(x.second);
    //dereferencing value of the pair
    auto fn_pair_value_deref = slambda(*x.second);

    // aplica a função fn sobre cada elemento do container
    // depois junta os resultados em uma string
    // separando os elementos com o delimiter
    // auto fn = [](auto v){return *v;};
    // std::vector<int*> vi = {new int(1), new int(2), new int(3)};
    // std::cout << utils::join(vi, ", ", fn) << '\n';
    std::string join(const auto& container, const std::string& delimiter, auto fn) {
        if(container.size() == 0)
            return "";
        std::ostringstream ss;
        for (const auto& item : container)
            ss << delimiter << fn(item);
        return ss.str().substr(delimiter.size());
    }

    // junta todos os elementos de um container numa string separando com o delimiter
    // join({"a", "b", "c"}, ",") -> "a,b,c"
    // join(std::vector<int>{1, 2, 3}, ",") -> "1,2,3"
    auto join(const auto& container, const std::string& delimiter) {
        return join(container, delimiter, fn_identity);
    }

    // junta todos os elementos de um container de ponteiros para objeto
    auto join_deref(const auto& container, const std::string& delimiter) {
        return join(container, delimiter, fn_deref);
    }

    // extrai um subvetor
    // extrai de início a fim, sem incluir o final
    // se não for passado o final, extrai até o final
    // se não for passado o início, extrai do início ao final
    // se o índice for negativo, conta a partir do final como no python e no js
    template <typename T>
    std::vector<T> slice(const std::vector<T>& container, int start = 0, int end = 0) {
        std::vector<T> result;
        if (end == 0)
            end = container.size();
        if (start < 0)
            start = container.size() + start;
        if (end < 0)
            end = container.size() + end;
        if (start >= end)
            return result;
        auto it_start = container.begin();
        auto it_end = container.begin();
        std::advance(it_start, start);
        std::advance(it_end, end);
        std::copy(it_start, it_end, std::back_inserter(result));
        return result;
    }

    // splits a stream in a vector of strings using delimiter ignoring empty strings
    // if used in cin, will fall in a infinite loop
    std::vector<std::string> split(std::istream& is, char delimiter) {
        std::vector<std::string> output;
        std::string token;
        while(std::getline(is, token, delimiter))
            if(token.size() > 0)
                output.push_back(token);
        return output;
    }

    // splits a line in a vector of strings using delimiter ignoring empty strings
    std::vector<std::string> split(const std::string& line, char delimiter) {
        std::istringstream ss(line);
        return split(ss, delimiter);
    }
}