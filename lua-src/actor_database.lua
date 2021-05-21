local ActorDatabase = {}
local this = ActorDatabase

function this:OnMailHandle(to_address,from_address,message)
    local json = message.json
    log("database this:OnMailHandle",Json.encode(json))
    if message.is_request then
        if json.method=="login" then
            local user_name=json.params.username
            local password = json.params.password
            log("Database login",user_name,password)
            local response= JsonRpc:ParseResponse(json.id,true)
            W.SendMail(from_address,to_address,Json.encode(response))
        end
    end
end

return this