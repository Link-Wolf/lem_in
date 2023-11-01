# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    scenari_calculator.py                              :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iCARUS <iCARUS@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/01 12:00:44 by iCARUS            #+#    #+#              #
#    Updated: 2023/11/01 13:42:26 by iCARUS           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import sys
import math

def get_tuples(length, total):
	if (length == 1):
		return [(total,)]
	ret = []

	for i in range(1, total + 1 - (length - 1)):
		for t in get_tuples(length - 1, total - i):
			ret.append((i,) + t)

	return ret

def lenght(t, ants, nb_pathes):
	turn = 0
	t = list(t)
	while (ants > 0):
		for i in range(nb_pathes):
			if (t[i] > 0):
				t[i] -= 1
			else:
				ants -= 1
		turn += 1
	return turn

if (len(sys.argv) != 4):
	print("Usage: ./scenari_calculator.py <number of ants> <number of paths> <number of rooms>")
	exit()

ants = int(sys.argv[1])
paths = int(sys.argv[2])
rooms = int(sys.argv[3])

result = []

for nb_pathes in range(paths, 0, -1):
	for nb_rooms in range(nb_pathes, rooms + 1):
		tuples = get_tuples(nb_pathes, nb_rooms)
		for t in tuples:
			result.append((t, lenght(t, ants, nb_pathes)))

result = sorted(
	result,
	key=lambda x: x[1]
)

for r in result:
	if (len(r[0]) == 2):
		print("1 path of length " + str(r[0][0]))
	print(r)
