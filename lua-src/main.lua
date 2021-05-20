require "base/app_config"

local actors_={}


function OnRegisterActors(app_type)
    if app_type==AppType_All then
        for key, value in pairs(Actor_Scripts) do
            local script = value[1]
            local address = value[2]
            RegisterActor(address)
            local actor = require(script)
            actors_[address]=actor
        end
    else
        local actor_script = Actor_Scripts[app_type]
        local script = actor_script[1]
        local address = actor_script[2]
        RegisterActor(address)
        local actor = require(script)
        actors_[address]=actor
    end
end


function OnMailHandle(to_address,from_address,json_message)
    local method_name="OnMailHandle"
    print("lua---",method_name,json_message)
    local actor  = actors_[to_address]
    if actor ~= nil then
        if actor[method_name]~=nil then
            actor[method_name](to_address,from_address,json_message)
        end
    end
end



print("main.lua----hello world")
log("xxx","safsdfs","111111","222222222",50)