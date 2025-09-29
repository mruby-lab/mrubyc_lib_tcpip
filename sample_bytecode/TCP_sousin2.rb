#このプログラムを動かすときは「ruby ファイル名 ポート番号」を入力
#終了する際はctrl+D

require "socket"
port = if ARGV.size > 0 then ARGV.shift else 4444 end

print port, "\n" #ポート番号を表示

socket = TCPSocket.open("127.0.0.1", port)
puts "サーバーに接続中(ポート番号#{port})"

puts "送信する内容を入力してください"
while 
  word=gets
  # socket.write(word)
  socket.send(word,0)
  # print(socket.gets)
end

puts '接続を終了します'
socket.close