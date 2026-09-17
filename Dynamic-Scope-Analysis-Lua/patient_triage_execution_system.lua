local function patient_workflow(patient_id, name, priority)
    coroutine.yield({
        patient_id = patient_id,
        name = name,
        priority = priority,
        stage = "Registration Complete"
    })

    coroutine.yield({
        patient_id = patient_id,
        name = name,
        priority = priority,
        stage = "Triage Complete"
    })

    coroutine.yield({
        patient_id = patient_id,
        name = name,
        priority = priority,
        stage = "Consultation Complete"
    })

    coroutine.yield({
        patient_id = patient_id,
        name = name,
        priority = priority,
        stage = "Discharged"
    })
end

local PRIORITY_WEIGHTS = {
    critical = 1,
    urgent   = 2,
    routine  = 3
}

local function run_hospital_scheduler(patients)
    local patient_list = {}

    for _, p in ipairs(patients) do
        table.insert(patient_list, {
            id = p.id,
            name = p.name,
            priority = p.priority,
            co = coroutine.create(patient_workflow),
            waiting_cycles = 0,
            started = false
        })
    end

    while #patient_list > 0 do
        table.sort(patient_list, function(a, b)
            local score_a = PRIORITY_WEIGHTS[a.priority] - (a.waiting_cycles * 0.5)
            local score_b = PRIORITY_WEIGHTS[b.priority] - (b.waiting_cycles * 0.5)

            if score_a == score_b then
                return a.id < b.id
            end
            return score_a < score_b
        end)

        local current = patient_list[1]

        if coroutine.status(current.co) ~= "dead" then
            local success, result
            if not current.started then
                current.started = true
                success, result = coroutine.resume(current.co, current.id, current.name, current.priority)
            else
                success, result = coroutine.resume(current.co)
            end

            if success and result then
                print(string.format("[Patient %d - %s (%s)]: Reached stage -> %s", 
                    result.patient_id, result.name, result.priority:upper(), result.stage))
                
                current.waiting_cycles = 0

                for i = 2, #patient_list do
                    patient_list[i].waiting_cycles = patient_list[i].waiting_cycles + 1
                end
            elseif not success then
                print(string.format("Error processing patient %d: %s", current.id, tostring(result)))
                table.remove(patient_list, 1)
            end

            if coroutine.status(current.co) == "dead" then
                table.remove(patient_list, 1)
            end
        else
            table.remove(patient_list, 1)
        end
    end
end

local patient_data = {
    { id = 101, name = "Amina",  priority = "routine"  },
    { id = 102, name = "Brian",  priority = "urgent"   },
    { id = 103, name = "Chuma",  priority = "critical" },
    { id = 104, name = "David",  priority = "routine"  }
}

run_hospital_scheduler(patient_data)