require "socket"

socket = TCPSocket.open("127.0.0.1", 12345) # この時点で3ウェイハンドシェイクによる接続を試みる
puts 'ソケットを接続中(ポート番号12345)'

socket.send("HELLO\nWORLD\n", 0)
puts '文字列を送信しました'

puts 'ソケットを終了します'
socket.close # FINを試みる
