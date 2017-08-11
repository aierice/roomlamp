#!/usr/bin/env ruby
# coding: utf-8


html = <<-"HTML"
HTTP/1.1 200 OK
Content-type:text/html

#{File.read(ARGV[0])}
HTML

htmldat = <<-"C"
char* html = #{
  html
      .inspect
      .gsub(/(\\n)/, "\\1\\\n")};
C

puts htmldat
File.write("html.h", htmldat)
