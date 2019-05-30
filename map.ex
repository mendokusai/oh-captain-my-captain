#!bin/elixir

# an elixiry implementation of map, filter, reduce

IO.puts "Hi"
numbers = System.argv

defmodule FunFunction do
  def mult_2(x) when is_integer(x) do
    x * 2
  end

  def mult_2(x) do
    String.to_integer(x) * 2
  end

  def div_3(x) when is_integer(x) do
    x / 3
  end

  def div_3(x) do
    String.to_integer(x) / 3
  end

  def map(array, fun, return \\ [])
  def map([], _fun, return), do: Enum.reverse(return)
  def map([number |tail], fun, return) do
    result = fun.(number)
    map(tail, fun, [result | return])
  end

  def filter(array, value, collection \\ [])
  def filter([], _value, collection), do: Enum.reverse(collection)
  def filter([head|tail], value, collection) do
    if head == value do
      filter(tail, value, [head|collection])
    else
      filter(tail, value, collection)
    end
  end

  def reduce(array, acc \\ 0)
  def reduce([], acc), do: acc
  def reduce([head | tail], acc) when is_integer(head) do
    reduce(tail, acc + head)
  end

  def reduce([head|tail], acc) when is_float(head) do
    reduce(tail, acc + head)
  end

  def reduce([head|tail], acc) do
    reduce(tail, acc + String.to_integer(head))
  end
end

IO.puts "Multiply Array by 2"
mult_array = FunFunction.map(numbers, &FunFunction.mult_2/1)
IO.inspect mult_array, label: "mult 2"
IO.inspect FunFunction.reduce(mult_array), label: "reduced mult_2"
IO.inspect FunFunction.filter(mult_array, 6), label: "filtered to 6"
IO.puts "\n"

IO.puts "Divide Multiply Array by 3"
div_array = FunFunction.map(mult_array, &FunFunction.div_3/1)

IO.inspect div_array, label: "div 3"
IO.inspect FunFunction.reduce(div_array), label: "reduced div_3"
IO.inspect FunFunction.filter(div_array, 2.0), label: "filtered to 2.0"
IO.puts "\n"

IO.inspect numbers, label: "orignal numbers - take that C!\n"
IO.inspect FunFunction.reduce(numbers), label: "reduced number strings"
IO.inspect FunFunction.filter(numbers, "2"), label: "filtered to '2'"
