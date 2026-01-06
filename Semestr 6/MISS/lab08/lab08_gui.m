function lab08_gui()
    % Create the figure
    f = figure('Name','Pendulum & Magnets Simulation','Position',[100 100 900 700]);
    
    % Axes on top - big area
    ax = axes('Units','pixels','Position',[50 250 800 400]);
    view(ax,3)
    grid(ax,'on')
    axis(ax,[-2 2 -2 2 -0.5 4])
    xlabel(ax,'X'); ylabel(ax,'Y'); zlabel(ax,'Z');
    hold(ax,'on');
    
    % Panel for inputs on the bottom
    panelHeight = 220;
    pnl = uipanel('Parent',f,'Units','pixels','Position',[0 0 900 panelHeight],...
                  'Title','Parametry symulacji');
    
    % Default parameters
    params.gravity = 9.81;
    params.damping = 0.1;
    params.refresh_time = 0.05;
    params.length = 1.0;
    params.mass = 1.0;
    params.x_start = 0.5;
    params.y_start = 0.5;
    params.mag_x = [0.5, -0.5];
    params.mag_y = [0.5, -0.5];
    params.mag_dist = [0.2, 0.2];
    params.mag_force = [1, -1];
    
    % Positions inside panel
    x1 = 20; x2 = 130; xw = 60; yw = 25; gap = 30;
    
    % Otoczenie
    uicontrol('Parent',pnl,'Style','text','Position',[x1 180 100 20],'String','Otoczenie:','FontWeight','bold');
    uicontrol('Parent',pnl,'Style','text','Position',[x1 150 80 20],'String','Grawitacja');
    gravEdit = uicontrol('Parent',pnl,'Style','edit','Position',[x2 150 xw yw],'String',num2str(params.gravity));
    
    uicontrol('Parent',pnl,'Style','text','Position',[x1 120 80 20],'String','Tłumienie');
    dampEdit = uicontrol('Parent',pnl,'Style','edit','Position',[x2 120 xw yw],'String',num2str(params.damping));
    
    uicontrol('Parent',pnl,'Style','text','Position',[x1 90 100 20],'String','Czas odświeżania');
    refreshEdit = uicontrol('Parent',pnl,'Style','edit','Position',[x2 90 xw yw],'String',num2str(params.refresh_time));
    
    % Wahadło
    x3 = 220; x4 = 330;
    uicontrol('Parent',pnl,'Style','text','Position',[x3 180 100 20],'String','Wahadło:','FontWeight','bold');
    uicontrol('Parent',pnl,'Style','text','Position',[x3 150 80 20],'String','Długość');
    lengthEdit = uicontrol('Parent',pnl,'Style','edit','Position',[x4 150 xw yw],'String',num2str(params.length));
    
    uicontrol('Parent',pnl,'Style','text','Position',[x3 120 80 20],'String','Masa kulki');
    massEdit = uicontrol('Parent',pnl,'Style','edit','Position',[x4 120 xw yw],'String',num2str(params.mass));
    
    uicontrol('Parent',pnl,'Style','text','Position',[x3 90 80 20],'String','X startowe');
    xstartEdit = uicontrol('Parent',pnl,'Style','edit','Position',[x4 90 xw yw],'String',num2str(params.x_start));
    
    uicontrol('Parent',pnl,'Style','text','Position',[x3 60 80 20],'String','Y startowe');
    ystartEdit = uicontrol('Parent',pnl,'Style','edit','Position',[x4 60 xw yw],'String',num2str(params.y_start));
    
    % Magnesy
    x5 = 420; x6 = 580; wMagEdit = 150;
    uicontrol('Parent',pnl,'Style','text','Position',[x5 180 120 20],'String','Magnesy:','FontWeight','bold');
    
    uicontrol('Parent',pnl,'Style','text','Position',[x5 150 120 20],'String','Wektor X (np. [1, 1])');
    magXEdit = uicontrol('Parent',pnl,'Style','edit','Position',[x6 150 wMagEdit yw],'String',mat2str(params.mag_x));
    
    uicontrol('Parent',pnl,'Style','text','Position',[x5 120 120 20],'String','Wektor Y (np. [1, 1])');
    magYEdit = uicontrol('Parent',pnl,'Style','edit','Position',[x6 120 wMagEdit yw],'String',mat2str(params.mag_y));
    
    uicontrol('Parent',pnl,'Style','text','Position',[x5 90 120 20],'String','Odległość od XY (np. [0.2, 0.2])');
    magDistEdit = uicontrol('Parent',pnl,'Style','edit','Position',[x6 90 wMagEdit yw],'String',mat2str(params.mag_dist));
    
    uicontrol('Parent',pnl,'Style','text','Position',[x5 60 120 20],'String','Siła (np. [1, -1])');
    magForceEdit = uicontrol('Parent',pnl,'Style','edit','Position',[x6 60 wMagEdit yw],'String',mat2str(params.mag_force));
    
    % Start button centered
    btn = uicontrol('Parent',pnl,'Style','pushbutton','Position',[400 10 120 40],'String','Start Simulation',...
        'FontSize',12,'Callback',@startSim);
    
    % Timer for simulation loop
    simTimer = timer('ExecutionMode','fixedRate','Period',params.refresh_time,'TimerFcn',@updateSim);
    
    simData = struct();
    
    function startSim(~,~)
        % Parse inputs, including vectors using str2num (expects [1,1] format)
        params.gravity = str2double(get(gravEdit,'String'));
        params.damping = str2double(get(dampEdit,'String'));
        params.refresh_time = str2double(get(refreshEdit,'String'));
        params.length = str2double(get(lengthEdit,'String'));
        params.mass = str2double(get(massEdit,'String'));
        params.x_start = str2double(get(xstartEdit,'String'));
        params.y_start = str2double(get(ystartEdit,'String'));
        
        try
            params.mag_x = str2num(get(magXEdit,'String')); %#ok<ST2NM>
            params.mag_y = str2num(get(magYEdit,'String')); %#ok<ST2NM>
            params.mag_dist = str2num(get(magDistEdit,'String')); %#ok<ST2NM>
            params.mag_force = str2num(get(magForceEdit,'String')); %#ok<ST2NM>
        catch
            errordlg('Błędne dane wektorów magnesów! Podaj je jako np. [1, 1]','Błąd');
            return;
        end
        
        % Validate vector lengths
        vecLengths = [length(params.mag_x), length(params.mag_y), length(params.mag_dist), length(params.mag_force)];
        if length(unique(vecLengths)) ~= 1
            errordlg('Wektory magnesów muszą mieć tę samą długość!','Błąd');
            return;
        end
        
        % Initialize simulation data
        simData.t = 0;
        simData.dt = params.refresh_time;
        simData.L = params.length;
        simData.m = params.mass;
        simData.xw = params.x_start;
        simData.yw = params.y_start;
        simData.xm = params.mag_x;
        simData.ym = params.mag_y;
        simData.dm = params.mag_dist;
        simData.am = params.mag_force;
        
        % Setup timer period
        stop(simTimer);
        simTimer.Period = params.refresh_time;
        start(simTimer);
    end

    function updateSim(~,~)
        % Simple pendulum swing simulation (replace with your model)
        simData.t = simData.t + simData.dt;
        
        xw = simData.L * sin(simData.t);
        yw = simData.L * cos(simData.t);
        
        % Calculate Z
        B = sqrt(xw^2 + yw^2);
        C = sqrt(simData.L^2 - B^2);
        Z = simData.L - C;
        
        % Plot
        cla(ax)
        plot3(ax, simData.xm(simData.am > 0), simData.ym(simData.am > 0), simData.dm(simData.am > 0), 'r.', 'MarkerSize', 20)
        hold(ax,'on')
        plot3(ax, simData.xm(simData.am < 0), simData.ym(simData.am < 0), simData.dm(simData.am < 0), 'b.', 'MarkerSize', 20)
        plot3(ax, xw, yw, Z, 'ko', 'MarkerSize', 20 * simData.m)
        plot3(ax, [0 xw], [0 yw], [simData.L Z], 'k-', 'LineWidth', 2)
        axis(ax,[-2 2 -2 2 -0.5 4])
        drawnow limitrate
    end

    % Cleanup timer on figure close
    f.CloseRequestFcn = @closeApp;
    function closeApp(~,~)
        try
            stop(simTimer);
            delete(simTimer);
        catch
        end
        delete(f);
    end
end
