def fibonacci(num):
  fib = [0, 1]
  while fib[-1] < num:
    new = fib[-1] + fib[-2]
    fib.append(new)

  return fib[:-1]


num = int(input("Digite um número:"))
result = fibonacci(num)
print(f"A sequencia de Fibonacci até o número {num} é: {result}")