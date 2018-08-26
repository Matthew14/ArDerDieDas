
with open('worter.csv', 'r') as f, open('der.txt', 'w') as der, open('die.txt', 'w') as die, open('das.txt', 'w') as das:
	for l in f.readlines():
		lsplitted = l.split(',')
		try:
			wort, article = lsplitted[0].strip().replace('"', '').split(' ')[1::-1]
		except:
			pass
		definition = lsplitted[1].strip().replace('"', '').split(' ')[0]

		print(article, wort, definition)

		if article == 'der':
			der.write('{},{}\n'.format(wort, definition))

		if article == 'die':
			die.write('{},{}\n'.format(wort, definition))

		if article == 'das':
			das.write('{},{}\n'.format(wort, definition))