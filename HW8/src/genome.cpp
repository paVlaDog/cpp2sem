#include "genome.h"

#include <algorithm>
#include <queue>
#include <stack>
#include <unordered_map>

namespace genome {

std::string assembly(const size_t k, const std::vector<std::string> & reads)
{
    if (k == 0 || reads.empty()) {
        return "";
    }
    std::unordered_map<std::string_view, std::pair<std::vector<std::string_view>, std::size_t>> allSubstr;
    for (const std::string_view st : reads) {
        for (size_t i = 0; i < st.size() - k; i++) {
            allSubstr[st.substr(i, k)].first.push_back(st.substr(i + 1, k));
            allSubstr[st.substr(i + 1, k)].second++;
        }
    }

    std::string_view start;
    for (auto const & el : allSubstr) {
        if (el.second.second < el.second.first.size()) {
            start = el.first;
            break;
        }
    }

    std::stack<std::string_view> st;
    std::string strAns{start};
    st.push(start);
    strAns.resize(strAns.size() + reads.size() * (reads[0].size() - k));
    auto counter = strAns.end();
    while (!st.empty()) {
        auto & edges = allSubstr[st.top()].first;
        if (edges.empty()) {
            *(--counter) = st.top()[st.top().size() - 1];
            st.pop();
        }
        else {
            st.push(edges.back());
            edges.pop_back();
        }
    }
    return strAns;
}

} // namespace genome
