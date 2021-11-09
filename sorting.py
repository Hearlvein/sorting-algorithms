from random import randrange as rr
from time import perf_counter
import matplotlib.pyplot as plt


def sort_native(ls: list) -> list:
	# Use sort without modifying the argument
	copy = ls[:]
	copy.sort()
	return copy


def sort_cstr(ls: list) -> list:
	out = [ls[0]]
	for e in ls[1:]:
		i = 0
		while i < len(out):
			if out[i] > e:
				out.insert(i, e)
				break
			i += 1
		if i == len(out):
			out.append(e)
	return out


print(sort_cstr([7, 4, 9, 6, 1, 2, 4, 0]))


def sort_min(ls: list) -> list:
	# This algorithm modifies the list it operates on
	copy = ls[:]
	out = []
	for k in range(len(ls)):
		# Find min
		min_j = 0
		for j in range(1, len(copy)):
			if copy[j] < copy[min_j]:
				min_j = j
		# Save the min, kick it from source
		out.append(copy[min_j])
		copy.pop(min_j)
	return out


def sort_bubble(ls: list) -> list:
	copy = ls[:]
	for _ in range(1, len(copy)):
		for i in range(1, len(copy)):
			if copy[i - 1] > copy[i]:
				copy[i - 1], copy[i] = copy[i], copy[i - 1]
	return copy


# print(sort_bubble([rr(0, 10) for k in range(20)]))


def merge_sorted(lhs: list, rhs: list) -> list:
	li = ri = 0
	out = []
	while li < len(lhs) and ri < len(rhs):
		if lhs[li] < rhs[ri]:
			out.append(lhs[li])
			li += 1
		else:
			out.append(rhs[ri])
			ri += 1
	if li < len(lhs):
		out.extend(lhs[li:])
	else:
		out.extend(rhs[ri:])
	return out


max_depth = 600
depth = 0


def disp(lbl: str, val):
	print('  ' * depth, lbl, val)


def sort_fusion(ls: list) -> list:
	if len(ls) < 2:
		return ls
	else:
		mid = len(ls) // 2
		return merge_sorted(
			sort_fusion(ls[:mid]),
			sort_fusion(ls[mid:])
		)


# funcs = [
# 	sort_native, sort_cstr,
# 	sort_min, sort_bubble,
# 	sort_fusion
# ]
# # sizes = [k for k in range(5, 1000)]
# perfs = [[] for _ in range(5)]
# for size in sizes:
# 	tab = [rr(0, 1000) for _ in range(size)]
# 	for i in range(len(funcs)):
# 		ta = perf_counter()
# 		res = funcs[i](tab)
# 		tb = perf_counter()
# 		perfs[i].append(tb - ta)
# plt.clf()
# for i in range(len(funcs)):
# 	plt.plot(sizes, perfs[i], label=f'{funcs[i].__name__}')
# plt.legend()
# plt.loglog()
# plt.show()
