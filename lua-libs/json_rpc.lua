--https://www.jsonrpc.org/specification

local JsonRpc = {}
local this = JsonRpc

function this:ParseRequest(id,method,params)
    if id ==nil then
        log(ERROR,"JSONRPC format error,id cannot be nil.")
    end
    local request = {}
    request.id=id
    request.jsonrpc="2.0"
    request.method= method
    request.params=params

    function request:to_json()
        return Json.encode(request)
    end

    return request
end

function this:ParseResponse(id,result,error)
    if id ==nil then
        log(ERROR,"JSONRPC format error,id cannot be nil.")
    end
    local response = {}
    response.id=id
    response.jsonrpc="2.0"
    response.result= result
    response.error=error

    function response:to_json()
        return Json.encode(response)
    end

    return response
end

function this:Parse(message)
    local jsonRpc ={}

    local json = Json.decode(message)
    jsonRpc.json = json

    jsonRpc.is_request =false
    jsonRpc.is_response = false
    jsonRpc.is_batch=false
    jsonRpc.notification =false
    
    local has_method = json.method ~= nil
    if has_method then
        local has_id = json.id ~= nil
        if has_id then
            jsonRpc.is_request=true
        else
            jsonRpc.notification=true
        end
    else
        jsonRpc.has_result = json.result~=nil
        jsonRpc.has_error = json.error ~= nil
        if jsonRpc.has_result or jsonRpc.has_error then
            jsonRpc.is_response=true
        else
            log(ERROR,"JSONRPC format error")
        end
    end

    function jsonRpc:to_json()
        return Json.encode(jsonRpc.json)
    end
    
    return jsonRpc
end

return this