#include <iostream>
#include <vector>
using namespace std;

int maxWaterStored(vector<int>& heights) {
    int n = heights.size();
    if (n == 0) return 0;

    vector<int> leftMax(n);
    vector<int> rightMax(n);
    int waterStored = 0;
    int totalWaterAmount = 0;

    // Điền vào mảng leftMax[]
    leftMax[0] = heights[0];
    for (int i = 1; i < n; i++) {
        leftMax[i] = max(leftMax[i - 1], heights[i]);
    }

    // Điền vào mảng rightMax[]
    rightMax[n - 1] = heights[n - 1];
    for (int i = n - 2; i >= 0; i--) {
        rightMax[i] = max(rightMax[i + 1], heights[i]);
    }

    // Tính toán lượng nước lưu trữ được
    for (int i = 0; i < n; i++) {
        waterStored = min(leftMax[i], rightMax[i]) - heights[i];
        totalWaterAmount += waterStored;
    }

    return totalWaterAmount;
}

int main() {
    vector<int> heights = {2, 2, 0, 9, 2, 0, 0, 4};
    int result = maxWaterStored(heights);
    cout << "Total water stored: " << result << endl;
    return 0;
}