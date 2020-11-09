#include <string>
#include <vector>

using std::vector;

class DerivedSubstring {
private:
    vector<vector<bool> > isDerived_;
    bool isEmptyWordDerived_ = false;
    vector<int> lengthMaxCommonSuffix_;

public:
    DerivedSubstring(const int size_);

    DerivedSubstring(char regularExpression, const std::string& word);

    DerivedSubstring& operator+=(const DerivedSubstring& other);

    DerivedSubstring& operator*=(const DerivedSubstring& other);

    DerivedSubstring operator*(const DerivedSubstring& second) const;

    bool operator==(const DerivedSubstring& other) const;
    bool operator!=(const DerivedSubstring& other) const;

    DerivedSubstring KleeneStar() const;

    int getLengthMaxCommonSuffix() const;
};

int solve(const std::string& regularExpression, const std::string& word);