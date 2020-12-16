#include <string>
#include <vector>

using std::vector;

class DerivedSubstring {
  private:
    vector<vector<bool>> isDerived_;
    bool isEmptyWordDerived_ = false;
    vector<int> lengthMaxCommonSuffix_;

  public:
    DerivedSubstring(const int size_);
    DerivedSubstring(char regularExpression, const std::string &word);
    DerivedSubstring(const vector<vector<bool>> &anotherIsDerived_, bool anotherIsEmptyWordDerived_,
                     const vector<int> &anotherLengthMaxCommonSuffix_);

    DerivedSubstring(const DerivedSubstring &another) = default;
    DerivedSubstring &operator=(const DerivedSubstring &another) = default;

    DerivedSubstring &operator+=(const DerivedSubstring &another);
    DerivedSubstring operator+(const DerivedSubstring &another) const;
    DerivedSubstring &operator*=(const DerivedSubstring &another);
    DerivedSubstring operator*(const DerivedSubstring &another) const;

    bool operator==(const DerivedSubstring &another) const;
    bool operator!=(const DerivedSubstring &another) const;

    DerivedSubstring KleeneStar() const;

    int getLengthMaxCommonSuffix() const;
};

int solve(const std::string &regularExpression, const std::string &word);