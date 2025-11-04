#実行方法：ruby ファイル名.rb ポート番号

require "socket"

# puts "ポート番号を入力してください"
port = 12345

socket = TCPSocket.open("172.26.18.116", port) # この時点で3ウェイハンドシェイクによる接続を試みる
puts "サーバーに接続中(ポート番号#{port})"

socket.send("HELLO\nWORLD\n", 0)
puts '文字列を送信しました'

while buf = socket.gets
  puts "#{buf}"
end

puts 'ソケットを終了します'
socket.close # FINを試みる
