local db = {}
local this = db

local data ={}


function this:Get(key)
    return data[key]
end

function this:Save(key,value)
    data[key]=value
end

return this