#include <iostream>
#include <vector>
#include <map>

struct Term {
    int coef; // hệ số
    int exp;  // bậc
    Term(int c, int e) : coef(c), exp(e) {}
};

class Polynomial {
public:
    std::vector<Term> terms;

    // Hàm thêm một hạng tử vào đa thức, chỉ thêm khi hệ số khác 0
    void addTerm(int coef, int exp) {
        if (coef != 0) {
            terms.emplace_back(coef, exp);
        }
    }

    // Hàm in các phần tử và vị trí lưu trữ
    void printDebugInfo(const std::string& name) const {
        std::cout << "Polynomial " << name << ":\n";
        for (size_t i = 0; i < terms.size(); ++i) {
            std::cout << "  Position " << i << ": coef=" << terms[i].coef << ", exp=" << terms[i].exp << "\n";
        }
    }
};

// Hàm cộng hai đa thức
Polynomial addPolynomials(const Polynomial& p1, const Polynomial& p2) {
    Polynomial result;
    size_t i = 0, j = 0;
    while (i < p1.terms.size() && j < p2.terms.size()) {
        if (p1.terms[i].exp == p2.terms[j].exp) {
            int coefSum = p1.terms[i].coef + p2.terms[j].coef;
            if (coefSum != 0) result.addTerm(coefSum, p1.terms[i].exp);
            ++i;
            ++j;
        } else if (p1.terms[i].exp > p2.terms[j].exp) {
            result.addTerm(p1.terms[i].coef, p1.terms[i].exp);
            ++i;
        } else {
            result.addTerm(p2.terms[j].coef, p2.terms[j].exp);
            ++j;
        }
    }
    // Thêm các phần tử còn lại
    while (i < p1.terms.size()) {
        result.addTerm(p1.terms[i].coef, p1.terms[i].exp);
        ++i;
    }
    while (j < p2.terms.size()) {
        result.addTerm(p2.terms[j].coef, p2.terms[j].exp);
        ++j;
    }
    return result;
}

// Hàm debug để in các biến cục bộ
void debugLocalVariables(const Polynomial& p1, const Polynomial& p2, const Polynomial& result) {
    std::cout << "\nDebugging local variables:\n";
    p1.printDebugInfo("P1");
    p2.printDebugInfo("P2");
    result.printDebugInfo("Result");
}

int main() {
    Polynomial p1, p2;

    // Thêm hạng tử vào đa thức P1
    p1.addTerm(3, 4);
    p1.addTerm(2, 3);
    p1.addTerm(-5, 1);

    // Thêm hạng tử vào đa thức P2
    p2.addTerm(4, 3);
    p2.addTerm(-3, 2);
    p2.addTerm(1, 0);

    // Tính đa thức tổng
    Polynomial result = addPolynomials(p1, p2);

    // In thông tin debug
    debugLocalVariables(p1, p2, result);

    return 0;
}
