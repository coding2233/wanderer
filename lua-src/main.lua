require "base/w"
require "base/app_config"
Json = require "json"
JsonRpc = require "json_rpc"

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
    local actor  = actors_[to_address]
    if actor ~= nil then
        if actor[method_name]~=nil then
            actor[method_name](actor,to_address,from_address,JsonRpc:Parse(json_message))
        end
    end
end


print("main.lua----hello world")