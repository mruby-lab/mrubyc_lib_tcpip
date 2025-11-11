ip = "192.168.128.173"
# ip = "172.29.247.212"

# require "socket"

# puts "ポート番号を入力してください"
port = 12345

socket = TCPSocket.open(ip, port) # この時点で3ウェイハンドシェイクによる接続を試みる
puts "サーバーに接続中(ポート番号#{port})"

TCPSocket.send("HELLO\nWORLD\n", 0)
puts '文字列を送信しました'

  # server = TCPServer.open("", port)
  # puts "サーバが待機中(ポート番号#{port})"
  # socket = TCPServer.accept
  # puts 'クライアントが接続しました'

puts '文字列を受信しました：'
puts TCPServer.recv(100)

# while buf = TCPServer.recv(100)
#   puts '文字列を受信しました：'
#   puts "#{buf}"
# end

puts 'ソケットを終了します'
TCPSocket.close # FINを試みる
TCPServer.close