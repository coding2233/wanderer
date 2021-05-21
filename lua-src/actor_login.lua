local ActorLogin = {}
local this = ActorLogin

local login_response_={}

---@param from_address integer
---@param to_address integer
---@param message JsonRpc
function this:OnMailHandle(to_address,from_address,message)
    local json = message.json
    log("[login OnMailHandle]",Json.encode(json))
    if message.is_request then
        if json.method=="login" then
            local user_name = json.params.username
            login_response_[json.id]={user_name,from_address}
            log("login 2 database",tostring(ActorAddress_DATABASE),tostring(to_address),Json.encode(json))
            W.SendMail(ActorAddress_DATABASE,to_address,Json.encode(json))
        end
    elseif message.is_response then
        local login_response = login_response_[message.id]
        if login_response~=nil then
            if login_response[1]==message.result.username then
                W.SendMail(login_response[2],to_address,Json.encode(json))
                login_response_[message.id]=nil
            end
        end
    end
end

return this