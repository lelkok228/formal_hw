#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

#include "MaxCommonSuffix.h"

using std::vector;

DerivedSubstring::DerivedSubstring(const int size_) : isDerived_(vector<vector<bool> >(size_, vector<bool>(size_, false))),
                                    isEmptyWordDerived_(true), lengthMaxCommonSuffix_(vector<int>(size_, 0)) {};

DerivedSubstring::DerivedSubstring(char regularExpression, const std::string& word) {
    isDerived_.assign(word.size(), vector<bool>(word.size(), false));
    lengthMaxCommonSuffix_.assign(word.size(), 0);
    if (regularExpression == '1') {
        isEmptyWordDerived_ = true;
        return ;
    }
    for (int i = 0; i < word.size(); ++i) {
        if (word[i] == regularExpression) {
            isDerived_[i][i] = true;
            lengthMaxCommonSuffix_[i] = 1;
        }
    }
}

DerivedSubstring& DerivedSubstring::operator+=(const DerivedSubstring& other) {
    isEmptyWordDerived_ |= other.isEmptyWordDerived_;
    for (int i = 0; i < isDerived_.size(); ++i) {
        for (int j = 0; j < isDerived_.size(); ++j) {
            isDerived_[i][j] = isDerived_[i][j] | other.isDerived_[i][j];
        }
    }

    for (int i = 0; i < lengthMaxCommonSuffix_.size(); ++i) {
        lengthMaxCommonSuffix_[i] = std::max(lengthMaxCommonSuffix_[i], other.lengthMaxCommonSuffix_[i]);
    }

    return *this;
}

DerivedSubstring& DerivedSubstring::operator*=(const DerivedSubstring& other) {
    vector<vector<bool> > resultIsDerived(isDerived_.size(), vector<bool>(isDerived_.size(), false));
    for (int i = 0; i < resultIsDerived.size(); ++i) {
        for (int j = i; j < resultIsDerived.size(); ++j) {
            for (int k = 1; k < j - i + 1; ++k) {
                resultIsDerived[i][j] = resultIsDerived[i][j] | (isDerived_[i][i + k - 1] & other.isDerived_[i + k][j]);
            }
            resultIsDerived[i][j] = resultIsDerived[i][j] | (isEmptyWordDerived_ & other.isDerived_[i][j]);
            resultIsDerived[i][j] = resultIsDerived[i][j] | (isDerived_[i][j] & other.isEmptyWordDerived_);
        }
    }

    vector<int> resultLengthMaxCommonSuffix = other.lengthMaxCommonSuffix_;
    for (int i = 1; i < other.isDerived_.size(); ++i) {
        for (int j = i; j < other.isDerived_.size(); ++j) {
            if (other.isDerived_[i][j]) {
                resultLengthMaxCommonSuffix[j] = std::max(resultLengthMaxCommonSuffix[j], (j - i + 1) + lengthMaxCommonSuffix_[i - 1]);
            }
        }
    }

    isEmptyWordDerived_ &= other.isEmptyWordDerived_;
    isDerived_ = resultIsDerived;
    lengthMaxCommonSuffix_ = resultLengthMaxCommonSuffix;
}

DerivedSubstring DerivedSubstring::operator*(const DerivedSubstring& second) const {
    DerivedSubstring first = *this;
    first *= second;
    return first;
}

bool DerivedSubstring::operator==(const DerivedSubstring& other) const {
    return isEmptyWordDerived_ == other.isEmptyWordDerived_ && isDerived_ == other.isDerived_ && lengthMaxCommonSuffix_ == other.lengthMaxCommonSuffix_;
}

bool DerivedSubstring::operator!=(const DerivedSubstring& other) const {
    return !(*this == other);
}

DerivedSubstring DerivedSubstring::KleeneStar() const {
    DerivedSubstring resultDerivedSubstring = DerivedSubstring(lengthMaxCommonSuffix_.size());
    DerivedSubstring currentDerivedSubstring = *this;
    DerivedSubstring nextDerivedSubstring = *this * currentDerivedSubstring;
    resultDerivedSubstring += currentDerivedSubstring;
    //result = A^0 + A^1; current = A^1; next = A^2;
    while (currentDerivedSubstring != nextDerivedSubstring) {
        resultDerivedSubstring += nextDerivedSubstring;
        currentDerivedSubstring = nextDerivedSubstring;
        nextDerivedSubstring *= *this;
    }
    return resultDerivedSubstring;
}

int DerivedSubstring::getLengthMaxCommonSuffix() const {
    return lengthMaxCommonSuffix_.back();
}

int solve(const std::string& regularExpression, const std::string& word) {
    vector<DerivedSubstring> stack_;
    for (int i = 0; i < regularExpression.size(); ++i) {
        if (regularExpression[i] == '+') {
            stack_[stack_.size() - 2] += stack_.back();
            stack_.pop_back();
        }
        else if (regularExpression[i] == '.') {
            stack_[stack_.size() - 2] *= stack_.back();
            stack_.pop_back();
        }
        else if (regularExpression[i] == '*') {
            stack_.back() = stack_.back().KleeneStar();
        }
        else {
            stack_.push_back(DerivedSubstring(regularExpression[i], word));
        }
    }

    return stack_.back().getLengthMaxCommonSuffix();
}