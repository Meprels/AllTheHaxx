luajit = {
	basepath = PathDir(ModuleFilename()),

	OptFind = function (name, required)
		local check = function(option, settings)
			option.value = false
			option.use_winlib = -1
			
			if family == "unix" then
				option.value = true
				option.use_winlib = 0
			elseif family == "windows" then
				if platform == "win32" then
					option.value = true
					option.use_winlib = 32
				elseif platform == "win64" then
					error("Compiling 64bit with CL is not available due to missing libraries. Please compile either with MinGW or switch to 32bit.")
			--		option.value = true
			--		option.use_winlib = 64
				end
			end
		end

		local apply = function(option, settings)
            settings.cc.includes:Add(luajit.basepath .. "/include")
            if option.use_winlib > 0 then
                settings.link.libpath:Add(luajit.basepath .. "/windows/lib" .. option.use_winlib)
                settings.link.libs:Add("lua51")
            elseif option.value == true then -- not windows but can have it anyway? -> build dynamically
                settings.link.libpath:Add(luajit.basepath .. "/unix")
               -- AddJob(luajit.basepath .. "/unix/libluajit.a", "Build LuaJIT lirary", "cd " .. luajit.basepath .. "/LuaJIT-2.0.2;make -j2 >NUL;cp src/libluajit.a ../unix/libluajit.a")
               -- TODO! XXX! HACK! this is run four times ALWAYS, but it does well. So I nevermind.
				ExecuteSilent("cd " .. luajit.basepath .. "/LuaJIT-2.0.2;make -j2 >NUL;rm NUL;cp -l src/libluajit.a ../unix/libluajit.a") -- build dynamically
				settings.link.libs:Add("luajit")
            end
		end

		local save = function(option, output)
			output:option(option, "value")
			output:option(option, "use_winlib")
		end

		local display = function(option)
            if option.value == true then
				if option.use_winlib == 32 then return "using supplied win32 libraries" end
			--	if option.use_winlib == 64 then return "using supplied win64 libraries" end
				return "building dynamically"
			else
				if option.required then
					return "not found (required)"
				else
					return "not found (optional)"
				end
			end
		end

		local o = MakeOption(name, 0, check, save, display)
		o.Apply = apply
		o.include_path = nil
		o.lib_path = nil
		o.required = required
		return o
	end
}
