# require "socket"

# puts "ポート番号を入力してください"
port = 12345

socket = TCPSocket.open("\"192.168.128.173\"", port) # この時点で3ウェイハンドシェイクによる接続を試みる
puts "サーバーに接続中(ポート番号#{port})"

socket.send("HELLO\nWORLD\n", 0)
puts '文字列を送信しました'

puts 'ソケットを終了します'
socket.close # FINを試みる
