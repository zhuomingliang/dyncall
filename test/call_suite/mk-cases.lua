function mkcase(id,sig)
  local h = { "/* ",id,":",sig," */ ",sig:sub(1,1), " f", id,"(",""}
  local t = { "fid=",id,";" }
  local pos = 0
  for i = 2, #sig do 
    pos = tostring(i-1)
    local name = "a"..pos
    local ch   = sig:sub(i,i)
    
    h[#h+1] = ch
    h[#h+1] = " "
    h[#h+1] = name
    h[#h+1] = ","

    t[#t+1] = "V_"
    t[#t+1] = ch
    t[#t+1] = "["
    t[#t+1] = pos
    t[#t+1] = "]"
    t[#t+1] = "="
    t[#t+1] = name
    t[#t+1] = ";"
  end
  h[#h] = "){"
  t[#t+1] = "ret_"
  t[#t+1] = sig:sub(1,1)
  t[#t+1] = "("
  t[#t+1] = pos
  t[#t+1] = ")"
  t[#t+1] = "};\n"
  return table.concat(h,"")..table.concat(t,"")
end

function mkfuntab(n)
  local s = { "void init_T(){\n"}
  for i = 1, n do
    s[#s+1] = "\tT["..i.."]=(void*)&f"..i..";\n"
  end
  s[#s+1] = "};\n"
  return table.concat(s,"")
end

function mkbatch()
  local lineno = 1
  for line in io.lines() do
    io.write(mkcase(lineno,line))
    lineno = lineno + 1
  end
  io.write(mkfuntab(lineno-1))
end

mkbatch()
-- print(mkcase(1,"vififififi"))

