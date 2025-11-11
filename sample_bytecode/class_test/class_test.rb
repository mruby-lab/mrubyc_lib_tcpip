# RubyからCで定義したmethod1を呼び出す例

puts "Ruby側から呼び出します"

# 引数なしで呼ぶ
result = MyClass.method1
puts "戻り値: #{result}"

# 引数ありで呼ぶ
result = MyClass.method1(42, "hello", [1, 2, 3])
puts "戻り値: #{result}"
