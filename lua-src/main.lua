local actor_scripts_={}
local actors_={}
actor_scripts_[1]="login"
actor_scripts_[2]="gateway"
actor_scripts_[4]="center"
actor_scripts_[8]="battle"
-- actor_scripts_[31]="all"

function OnRegisterActors(app_type)
    print("lua RegisterActors",app_type)
    local actor_script = actor_scripts_[app_type]
    if actor_script == nil then
        
    end
end

function showinfo()
print("main.lua ------------ showinfo")
end


print("main.lua----hello world")