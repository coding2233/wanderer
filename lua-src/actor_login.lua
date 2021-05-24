local ActorLogin = {}
local this = ActorLogin

local login_response_={}
local token_response_ = {}

---@param from_address integer
---@param to_address integer
---@param message JsonRpc
function this:OnMailHandle(to_address,from_address,message)
    local json = message.json
    log("[login OnMailHandle]",Json.encode(json))
    if message.is_request then
        if json.method=="login" then
            local user_name = json.params.username
            if login_response_[json.id] ~=nil then
                log(ERROR,"The JSONRPC data processed by the actor_login contains the same ID.")
            end
            local id = this:RandomId()
            login_response_[id]={json.id,user_name,from_address}
            json.id = id
            log("login 2 database",tostring(ActorAddress_DATABASE),tostring(to_address),Json.encode(json))
            W.SendMail(ActorAddress_DATABASE,to_address,Json.encode(json))
        end
    elseif message.is_response then
        local login_response = login_response_[json.id]
        if login_response~=nil then
            if message.result.sccuess then
                local id = this:RandomId()
                local request = JsonRpc:ParseRequest(id,"GetToken",{username=message.result.username})
                token_response_[id]={json.id,message.result.username}
                -- W.SendMail(ActorAddress_GATEWAY,)
            end
            -- if login_response[1]==message.result.username then
            --     -- W.SendMail(login_response[2],to_address,Json.encode(json))
            --     -- login_response_[message.id]=nil
            -- end
        end
    end
end

function this:RandomId()
    local id=0
    while id==0 do
        local id = math.random(math.mininteger,math.maxinteger)
        local lr = login_response_[id]
        local tr = token_response_[id]
        if lr ~= nil or tr ~= nil then
            id =0
        end
    end
    return id
end

return this