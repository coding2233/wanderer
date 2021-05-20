local ActorLogin = {}
local this = ActorLogin

function this:OnMailHandle(to_address,from_address,json_message)
    print("actor-login   function this:OnMailHandle(to_address,from_address,json_message) ")
end

return this