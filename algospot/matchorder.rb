#!/usr/bin/env ruby

C = ARGF.readline.to_i
C.times do |c|
  n = ARGF.readline.to_i
  rus = ARGF.readline.split(" ").map(&:to_i).sort
  kor = ARGF.readline.split(" ").map(&:to_i).sort
  win = 0
  rus_i = 0
  kor_i = 0
  while rus_i < n && kor_i < n
    while kor_i < n && kor[kor_i] < rus[rus_i]
      kor_i += 1
    end
    if kor_i < n
      win += 1
      rus_i += 1
      kor_i += 1
    end
  end
  p win
end
