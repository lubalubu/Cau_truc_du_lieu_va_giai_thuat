def sort_colors(colors):
    red_count = colors.count('đỏ')
    white_count = colors.count('trắng')
    blue_count = colors.count('xanh')

    sorted_colors = ['đỏ'] * red_count + ['trắng'] * white_count + ['xanh'] * blue_count
    return sorted_colors

n = int(input("Nhập số lượng màu: "))
colors = []

print("Nhập các màu (đỏ, trắng, xanh):")
for _ in range(n):
    color = input().strip()
    colors.append(color)

sorted_colors = sort_colors(colors)

print("Kết quả sau khi sắp xếp:")
print(' '.join(sorted_colors))
