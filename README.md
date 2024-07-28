<h1>Minishell</h1>

<h2>Project Overview</h2>
<p>The <code>minishell</code> project is about creating a simple shell similar to bash. Through this project, you will learn a lot about processes and file descriptors.</p>

<h2>Purpose</h2>
<p>The purpose of this project is to write a C program that functions as a basic shell. This involves handling user input, executing commands, managing processes, and implementing standard shell features.</p>

<h2>What You Will Learn</h2>
<ul>
    <li>How to create and manage processes in C.</li>
    <li>How to handle file descriptors and I/O redirection.</li>
    <li>How to implement a command-line interface with basic shell functionalities.</li>
    <li>How to manage environment variables and signal handling.</li>
</ul>

<h2>Project Contents</h2>

<h3>Mandatory Part</h3>
<p>You must implement the following requirements:</p>
<ul>
    <li>Write a program named <code>minishell</code> that provides the following features:
        <ul>
            <li>Display a prompt when waiting for a new command.</li>
            <li>Have a working history.</li>
            <li>Search and launch the right executable (based on the PATH variable or using a relative or an absolute path).</li>
            <li>Use only one global variable to indicate a received signal.</li>
            <li>Handle single quotes (<code>'</code>) and double quotes (<code>"</code>).</li>
            <li>Implement input (<code><</code>) and output (<code>></code>) redirection, as well as append (<code>>></code>) and heredoc (<code><<</code>) functionality.</li>
            <li>Implement pipes (<code>|</code>) to connect the output of one command to the input of the next.</li>
            <li>Handle environment variables (e.g., <code>$VAR</code>).</li>
            <li>Handle <code>$?</code> to expand to the exit status of the most recently executed foreground pipeline.</li>
            <li>Handle <code>ctrl-C</code>, <code>ctrl-D</code>, and <code>ctrl-\</code> similarly to bash.</li>
            <li>Implement the following built-in commands:
                <ul>
                    <li><code>echo</code> with option <code>-n</code></li>
                    <li><code>cd</code> with a relative or absolute path</li>
                    <li><code>pwd</code> with no options</li>
                    <li><code>export</code> with no options</li>
                    <li><code>unset</code> with no options</li>
                    <li><code>env</code> with no options or arguments</li>
                    <li><code>exit</code> with no options</li>
                </ul>
            </li>
        </ul>
    </li>
</ul>

<h3>Bonus Part</h3>
<p>The bonus part includes additional features:</p>
<ul>
    <li>Implement logical operators <code>&&</code> and <code>||</code> with parenthesis for priorities.</li>
    <li>Implement wildcard <code>*</code> for the current working directory.</li>
</ul>
<p>The bonus part will only be assessed if the mandatory part is perfect.</p>

<h2>Usage</h2>
<p>To use the <code>minishell</code> program, compile it using the provided Makefile and run it. The shell will display a prompt where you can enter commands, and it will execute them, supporting the features described above.</p>

<h2>Conclusion</h2>
<p>The <code>minishell</code> project provides an opportunity to learn about process management, file descriptors, and command-line interface development in C. By completing this project, you will gain valuable skills in creating and managing a basic shell environment.</p>
