#!/usr/bin/env ruby

T = ARGF.readline.to_i
T.times do |t|
  n = ARGF.readline.to_i
  m = ARGF.readline.split(" ").map(&:to_i)
  e = ARGF.readline.split(" ").map(&:to_i)
  a = e.zip(m).sort.reverse
  m_sum = 0
  max_t = 0
  a.each do |ei, mi|
    m_sum += mi
    max_t = [max_t, m_sum + ei].max
  end
  p max_t
end
