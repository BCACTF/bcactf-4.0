
### Take inputs for required 2 nums and 1 operator ###
num = input()
num2 = input()
op = input()

### Check if op is a valid operator ###
### If no, then raise error ###
if not op in ['+', '-', '*', '/', '^']:
	raise SyntaxError('Read token %s, expected operator' % op)
### Else, calculate new answer ###
answer = eval(f'{num}{op}{num2}')

num = input()

### Take inputs for more nums and operators ###
while num != '=':
	op = input()
### If not '=' or invalid, then calculate new answer ###
	if not op in ['+', '-', '*', '/', '^']:
		raise SyntaxError('Read token %s, expected operator' % op)
	answer = eval(f'{answer} {op} {float(num)}')
	num = input()

### Output final answer ###
print(answer)