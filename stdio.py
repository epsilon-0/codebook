from sys import stdin, stdout


class StdIO:
    def __init__(self, delimiter=" "):
        self.line = []
        self.delimiter = delimiter
        return

    def next(self, input_type=str):
        if self.line == []:
            self.line = stdin.readline().strip().split(self.delimiter)
            self.line.reverse()
        return input_type(self.line.pop())

    def write(self, line, ending="\n"):
        stdout.write(str(line))
        stdout.write(ending)
