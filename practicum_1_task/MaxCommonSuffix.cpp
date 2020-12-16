#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "MaxCommonSuffix.h"

using std::vector;

DerivedSubstring::DerivedSubstring(const int size_)
    : isDerived_(vector<vector<bool>>(size_, vector<bool>(size_, false))), isEmptyWordDerived_(true),
      lengthMaxCommonSuffix_(vector<int>(size_, 0)){};

DerivedSubstring::DerivedSubstring(char regularExpression, const std::string &word) {
    isDerived_.assign(word.size(), vector<bool>(word.size(), false));
    lengthMaxCommonSuffix_.assign(word.size(), 0);
    if (regularExpression == '1') {
        isEmptyWordDerived_ = true;
        return;
    }
    for (int i = 0; i < word.size(); ++i) {
        if (word[i] == regularExpression) {
            isDerived_[i][i] = true;
            lengthMaxCommonSuffix_[i] = 1;
        }
    }
}

DerivedSubstring::DerivedSubstring(const vector<vector<bool>> &anotherIsDerived_, bool anotherIsEmptyWordDerived_,
                                   const vector<int> &anotherLengthMaxCommonSuffix_)
    : isDerived_(anotherIsDerived_), isEmptyWordDerived_(anotherIsEmptyWordDerived_),
      lengthMaxCommonSuffix_(anotherLengthMaxCommonSuffix_){};

DerivedSubstring &DerivedSubstring::operator+=(const DerivedSubstring &another) {
    isEmptyWordDerived_ |= another.isEmptyWordDerived_;
    for (int i = 0; i < isDerived_.size(); ++i) {
        for (int j = 0; j < isDerived_.size(); ++j) {
            isDerived_[i][j] = isDerived_[i][j] | another.isDerived_[i][j];
        }
    }

    for (int i = 0; i < lengthMaxCommonSuffix_.size(); ++i) {
        lengthMaxCommonSuffix_[i] = std::max(lengthMaxCommonSuffix_[i], another.lengthMaxCommonSuffix_[i]);
    }

    return *this;
}

DerivedSubstring DerivedSubstring::operator+(const DerivedSubstring &another) const {
    DerivedSubstring resDerivedSubstring = *this;
    return resDerivedSubstring += another;
}

DerivedSubstring &DerivedSubstring::operator*=(const DerivedSubstring &another) {
    vector<vector<bool>> resultIsDerived(isDerived_.size(), vector<bool>(isDerived_.size(), false));
    for (int i = 0; i < resultIsDerived.size(); ++i) {
        for (int j = i; j < resultIsDerived.size(); ++j) {
            for (int k = 1; k < j - i + 1; ++k) {
                resultIsDerived[i][j] =
                    resultIsDerived[i][j] | (isDerived_[i][i + k - 1] & another.isDerived_[i + k][j]);
            }
            resultIsDerived[i][j] = resultIsDerived[i][j] | (isEmptyWordDerived_ & another.isDerived_[i][j]);
            resultIsDerived[i][j] = resultIsDerived[i][j] | (isDerived_[i][j] & another.isEmptyWordDerived_);
        }
    }

    vector<int> resultLengthMaxCommonSuffix = another.lengthMaxCommonSuffix_;
    if (another.isEmptyWordDerived_) {
        for (int i = 0; i < resultLengthMaxCommonSuffix.size(); ++i) {
            resultLengthMaxCommonSuffix[i] = std::max(resultLengthMaxCommonSuffix[i], lengthMaxCommonSuffix_[i]);
        }
    }
    for (int i = 1; i < another.isDerived_.size(); ++i) {
        for (int j = i; j < another.isDerived_.size(); ++j) {
            if (another.isDerived_[i][j]) {
                resultLengthMaxCommonSuffix[j] =
                    std::max(resultLengthMaxCommonSuffix[j], (j - i + 1) + lengthMaxCommonSuffix_[i - 1]);
            }
        }
    }

    isEmptyWordDerived_ &= another.isEmptyWordDerived_;
    isDerived_ = resultIsDerived;
    lengthMaxCommonSuffix_ = resultLengthMaxCommonSuffix;

    return *this;
}

DerivedSubstring DerivedSubstring::operator*(const DerivedSubstring &another) const {
    DerivedSubstring resDerivedSubstring = *this;
    return resDerivedSubstring *= another;
}

bool DerivedSubstring::operator==(const DerivedSubstring &another) const {
    return isEmptyWordDerived_ == another.isEmptyWordDerived_ && isDerived_ == another.isDerived_ &&
           lengthMaxCommonSuffix_ == another.lengthMaxCommonSuffix_;
}

bool DerivedSubstring::operator!=(const DerivedSubstring &another) const { return !(*this == another); }

DerivedSubstring DerivedSubstring::KleeneStar() const {
    DerivedSubstring resultDerivedSubstring = DerivedSubstring(lengthMaxCommonSuffix_.size());
    DerivedSubstring currentDerivedSubstring = *this;
    DerivedSubstring nextDerivedSubstring = *this * currentDerivedSubstring;
    resultDerivedSubstring += currentDerivedSubstring;
    // result = A^0 + A^1; current = A^1; next = A^2;
    while (currentDerivedSubstring != nextDerivedSubstring) {
        resultDerivedSubstring += nextDerivedSubstring;
        currentDerivedSubstring = nextDerivedSubstring;
        nextDerivedSubstring *= *this;
    }
    return resultDerivedSubstring;
}

int DerivedSubstring::getLengthMaxCommonSuffix() const { return lengthMaxCommonSuffix_.back(); }

int solve(const std::string &regularExpression, const std::string &word) {
    vector<DerivedSubstring> stack_;
    for (int i = 0; i < regularExpression.size(); ++i) {
        if (regularExpression[i] == '+') {
            stack_[stack_.size() - 2] += stack_.back();
            stack_.pop_back();
        } else if (regularExpression[i] == '.') {
            stack_[stack_.size() - 2] *= stack_.back();
            stack_.pop_back();
        } else if (regularExpression[i] == '*') {
            stack_.back() = stack_.back().KleeneStar();
        } else {
            stack_.push_back(DerivedSubstring(regularExpression[i], word));
        }
    }

    return stack_.back().getLengthMaxCommonSuffix();
}